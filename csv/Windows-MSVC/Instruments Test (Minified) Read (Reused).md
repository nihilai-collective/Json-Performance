
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1721.86 | 0.0679353 | 6351.19ms | 108313 | 4890 | 8.12199e+06 | 59990.4 | 0.492725 | 1.43721 | 1(Win) | true |
| Jsonifier (two-stage) | 1237.37 | 0.373466 | 8844.5ms | 108313 | 160 | 1.55521e+07 | 83480 | 0.228573 | 2.00012 | 2(Loss) | true |
| Glaze | 1098.16 | 0.575459 | 5143.85ms | 108313 | 40 | 1.17198e+07 | 94062.5 | 0.411878 | 2.25391 | 3(Loss) | true |
| simdjson (ondemand) | 941.76 | 0.863626 | 5910.39ms | 108313 | 30 | 2.69187e+07 | 109683 | 0.112571 | 2.62793 | 4(Loss) | true |
