
----
### Github Events Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1087.19 | 0.494794 | 4777.12ms | 53331 | 1280 | 6.85821e+07 | 46781.7 | 0.441819 | 2.2757 | 1(Win) | true |
| Glaze | 982.41 | 0.25504 | 5272.22ms | 53331 | 2560 | 4.46303e+07 | 51771.1 | 0.669566 | 2.51853 | 2(Loss) | true |
| Jsonifier (two-stage) | 961.967 | 0.685915 | 5491.58ms | 53331 | 80 | 1.05213e+07 | 52871.2 | 0.224099 | 2.57178 | 3(Loss) | true |
| simdjson (ondemand) | 633.513 | 0.159469 | 8171.33ms | 53331 | 2560 | 4.19607e+07 | 80283.1 | 0.480541 | 3.90664 | 4(Loss) | true |
