import { NgModule, ModuleWithProviders, SkipSelf, Optional } from '@angular/core';
import { lthnConfiguration } from './configuration';
import { HttpClient } from '@angular/common/http';


@NgModule({
  imports:      [],
  declarations: [],
  exports:      [],
  providers: []
})
export class lthnApiModule {
    public static forRoot(configurationFactory: () => lthnConfiguration): ModuleWithProviders<lthnApiModule> {
        return {
            ngModule: lthnApiModule,
            providers: [ { provide: lthnConfiguration, useFactory: configurationFactory } ]
        };
    }

    constructor( @Optional() @SkipSelf() parentModule: lthnApiModule,
                 @Optional() http: HttpClient) {
        if (parentModule) {
            throw new Error('lthnApiModule is already loaded. Import in your base AppModule only.');
        }
        if (!http) {
            throw new Error('You need to import the HttpClientModule in your AppModule! \n' +
            'See also https://github.com/angular/angular/issues/20575');
        }
    }
}
