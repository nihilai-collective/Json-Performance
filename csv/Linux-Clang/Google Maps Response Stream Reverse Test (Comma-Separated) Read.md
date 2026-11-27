
----
### Google Maps Response Stream Reverse Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 736.052 | 0.454068 | 8598.08ms | 4203058 | 80 | 4.89153e+10 | 5.44574e+06 | 0.123883 | 6.8814 | 29.801 | 6.07565 | 0.0270871 | 0.0890527 | 0.00914544 | 1(Win) | true |
| simdjson (ondemand) | 627.659 | 0.443356 | 10008.9ms | 4203058 | 80 | 6.41325e+10 | 6.38619e+06 | 0.2482 | 8.11867 | 32.6837 | 5.94564 | 0.0289624 | 0.104274 | 0.0112778 | 2(Loss) | true |
