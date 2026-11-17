
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2070.59 | 0.127716 | 2903.87ms | 53331 | 2560 | 2.51944e+06 | 24563.3 | 0.093064 | 1.19441 | 1(Win) | true |
| Jsonifier (two-stage) | 2051.51 | 0.174883 | 3024.83ms | 53331 | 1280 | 2.40613e+06 | 24791.7 | 0.18133 | 1.20539 | 2(Loss) | true |
| simdjson (reflection) | 2019.33 | 0.130873 | 3056.58ms | 53331 | 2560 | 2.78151e+06 | 25186.7 | 0.599057 | 1.22475 | 3(Loss) | true |
| Glaze | 1839.18 | 0.137729 | 3264.59ms | 53331 | 1280 | 1.85684e+06 | 27653.9 | 0.0476822 | 1.3448 | 4(Loss) | true |
| simdjson (ondemand) | 1441.24 | 0.549979 | 3988.64ms | 53331 | 30 | 1.13006e+06 | 35289.4 | 0.379499 | 1.7165 | 5(Loss) | true |
