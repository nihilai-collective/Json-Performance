
----
### Twitter Partial Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 4834.91 | 0.0596687 | 6482.64ms | 631514 | 2560 | 1.41424e+07 | 124565 | 0.163023 | 1(Win) | true |
| Jsonifier | 4770.99 | 0.348346 | 6603.98ms | 631514 | 1280 | 2.47502e+08 | 126233 | 0.594542 | 2(Loss) | true |
| Jsonifier (two-stage) | 4226.49 | 0.349272 | 7168.45ms | 631514 | 2560 | 6.34126e+08 | 142496 | 0.380045 | 3(Loss) | true |
| simdjson (ondemand) | 4100.12 | 0.876422 | 7658.76ms | 631514 | 160 | 2.65167e+08 | 146888 | 0.389523 | 4(Loss) | true |
| Glaze | 2891.32 | 0.574805 | 5331.1ms | 631514 | 30 | 4.30067e+07 | 208299 | 0.0777764 | 5(Loss) | true |
