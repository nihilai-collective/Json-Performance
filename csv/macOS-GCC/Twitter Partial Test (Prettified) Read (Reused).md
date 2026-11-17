
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4845.58 | 0.555952 | 6400.36ms | 631514 | 320 | 1.52792e+08 | 124290 | 0.209626 | 1(Win) | true |
| Jsonifier | 4625.1 | 0.524588 | 6430.27ms | 631514 | 640 | 2.98634e+08 | 130215 | 0.548067 | 2(Loss) | true |
| simdjson (ondemand) | 4342.51 | 0.286093 | 7911.69ms | 631514 | 640 | 1.00758e+08 | 138689 | 1.09002 | 3(Loss) | true |
| simdjson (reflection) | 4285.06 | 0.304619 | 7383.16ms | 631514 | 1280 | 2.34626e+08 | 140548 | 2.50554 | 4(Loss) | true |
| Glaze | 3091.18 | 0.14731 | 5230.95ms | 631514 | 320 | 2.6359e+07 | 194831 | 0.219336 | 5(Loss) | true |
