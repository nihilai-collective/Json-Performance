
----
### Twitter Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 754.01 | 0.0986717 | 8383.41ms | 4219119 | 30 | 8.31756e+08 | 5.33635e+06 | 0.250041 | 6.72263 | 26.3382 | 4.97764 | 0.0169592 | 0.0578287 | 0.00277338 | 1(Win) | true |
| simdjson (ondemand) | 276.456 | 0.149014 | 10418.6ms | 4219119 | 40 | 1.8815e+10 | 1.45544e+07 | 0.188144 | 18.2638 | 72.3589 | 12.6015 | 0.0868096 | 0.0537844 | 0.0149669 | 2(Loss) | true |
