
----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 9874.06 | 0.354966 | 22.5861ms | 1996 | 4890 | 2289.87 | 192.781 | 1.54729 | 0.214258 | 1(Win) | true |
| Glaze | 3402.49 | 0.717485 | 64.7236ms | 1996 | 2560 | 41247.1 | 559.453 | 0.0698714 | 0.680393 | 2(Loss) | true |
