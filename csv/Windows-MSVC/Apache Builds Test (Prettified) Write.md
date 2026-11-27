
----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10346.1 | 0.471877 | 1291.91ms | 136037 | 1280 | 4.48151e+06 | 12539.5 | 0.455006 | 0.238648 | 1(Win) | true |
| Glaze | 3854.52 | 0.283533 | 3440.15ms | 136076 | 4890 | 4.45592e+07 | 33667.5 | 0.0788192 | 0.641741 | 2(Loss) | true |
