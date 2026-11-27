
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2156.55 | 0.322157 | 5381.79ms | 94653 | 320 | 5.81882e+06 | 41857.7 | 0.316923 | 1.14728 | 1(Win) | true |
| Jsonifier (two-stage) | 1819.4 | 0.0668455 | 6205.86ms | 94653 | 4890 | 5.37856e+06 | 49614.2 | 0.55482 | 1.36002 | 2(Loss) | true |
| Glaze | 1755.6 | 0.189531 | 6413.95ms | 94653 | 640 | 6.07796e+06 | 51417.3 | 0.144856 | 1.40949 | 3(Loss) | true |
| simdjson (reflection) | 1746.11 | 0.0866644 | 6321.39ms | 94653 | 4890 | 9.81558e+06 | 51696.7 | 0.978805 | 1.41715 | 4(Loss) | true |
| simdjson (ondemand) | 1722.71 | 0.252359 | 6497.18ms | 94653 | 160 | 2.79773e+06 | 52399.1 | 0.625275 | 1.43644 | 5(Loss) | true |
