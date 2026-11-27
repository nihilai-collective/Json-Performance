
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2019.13 | 0.141511 | 167.727ms | 2889 | 640 | 2386.32 | 1364.53 | 0.0572213 | 1.20239 | 1(Win) | true |
| Glaze | 1519.04 | 0.235059 | 206.849ms | 2889 | 80 | 1454.11 | 1813.75 | 0.207182 | 1.60889 | 2(Loss) | true |
| Jsonifier (two-stage) | 1421.1 | 0.370624 | 223.841ms | 2889 | 2560 | 132175 | 1938.75 | 0.560987 | 1.71558 | 3(Loss) | true |
| simdjson (ondemand) | 1278.31 | 0.129151 | 243.353ms | 2889 | 320 | 2479.53 | 2155.31 | 0.363795 | 1.91538 | 4(Loss) | true |
