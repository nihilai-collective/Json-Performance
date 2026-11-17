
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2282.96 | 0.253821 | 2990.88ms | 56369 | 1280 | 4.57249e+06 | 23547.4 | 1.69554 | 1(Win) | true |
| Glaze | 1720.52 | 0.277879 | 3689.1ms | 56369 | 4890 | 3.6862e+07 | 31244.9 | 0.25133 | 2(Loss) | true |
| Jsonifier (two-stage) | 1363.95 | 0.298741 | 4718.21ms | 56369 | 2560 | 3.54909e+07 | 39413.3 | 0.532335 | 3(Loss) | true |
| simdjson (reflection) | 1134.56 | 0.256649 | 5331.71ms | 56369 | 2560 | 3.78569e+07 | 47382 | 0.185801 | 4(Loss) | true |
| simdjson (ondemand) | 1083.54 | 0.147458 | 5600.84ms | 56369 | 2560 | 1.37016e+07 | 49613.2 | 0.244497 | 5(Loss) | true |
