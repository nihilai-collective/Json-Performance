
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8462.46 | 0.496773 | 761.162ms | 2963 | 2560 | 7044.11 | 333.914 | 0.551791 | 0.682025 | 1.42592 | 0.226122 | 0.000416069 | 5.26019e-05 | 2.80807e-05 | 1(Win) | true |
| Glaze | 4231.06 | 0.223675 | 794.183ms | 2963 | 4890 | 10912.1 | 667.856 | 0.328394 | 1.27537 | 3.22545 | 0.484645 | 0.000346537 | 5.87339e-05 | 2.05672e-05 | 2(Loss) | true |
