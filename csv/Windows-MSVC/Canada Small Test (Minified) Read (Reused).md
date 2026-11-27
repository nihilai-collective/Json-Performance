
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 659.289 | 0.234325 | 838.299ms | 4630 | 2560 | 630501 | 6697.38 | 0.146182 | 3.73971 | 1(Win) | true |
| Jsonifier (two-stage) | 642.958 | 0.150998 | 866.736ms | 4630 | 40 | 4301.28 | 6867.5 | 0.0607091 | 3.8371 | 2(Loss) | true |
| simdjson (ondemand) | 180.879 | 0.103952 | 2609.11ms | 4630 | 4890 | 3.14891e+06 | 24411.3 | 0.683686 | 13.6713 | 3(Loss) | true |
| Glaze | 171.745 | 0.203428 | 2796.19ms | 4630 | 1280 | 3.50127e+06 | 25709.7 | 0.194858 | 14.4003 | 4(Loss) | true |
