
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1508.47 | 0.564382 | 8065.34ms | 500299 | 640 | 2.03944e+09 | 316295 | 0.0762825 | 2.01442 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 1129.34 | 0.771839 | 5362.22ms | 500299 | 640 | 6.80524e+09 | 422479 | 2.66829 | 2.69042 | -(Loss) | false |
| Glaze | 748.546 | 1.12021 | 7962.27ms | 500299 | 640 | 3.26287e+10 | 637399 | 0.815171 | 4.05961 | 3(Loss) | true |
| simdjson (ondemand) | 551.783 | 1.01645 | 5544.4ms | 500299 | 160 | 1.23599e+10 | 864692 | 0.457024 | 5.50735 | 4(Loss) | true |
