
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 608.346 | 0.0502408 | 845.325ms | 4604 | 4890 | 64297.1 | 7217.46 | 0.0459374 | 4.9822 | 1(Win) | true |
| Jsonifier | 582.658 | 0.152963 | 879.226ms | 4604 | 4890 | 649720 | 7535.66 | 0.105347 | 5.20186 | 2(Loss) | true |
| simdjson (ondemand) | 368.596 | 0.0432257 | 1299.03ms | 4604 | 4890 | 129647 | 11912 | 0.274601 | 8.22987 | 3(Loss) | true |
| Glaze | 330.792 | 0.0873828 | 1448.68ms | 4604 | 4890 | 657841 | 13273.3 | 0.0193215 | 9.17372 | 4(Loss) | true |
