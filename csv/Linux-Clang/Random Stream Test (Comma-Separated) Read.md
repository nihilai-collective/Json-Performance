
----
### Random Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1289.45 | 0.455615 | 5749.86ms | 4506446 | 40 | 9.22392e+09 | 3.33296e+06 | 0.146241 | 3.93144 | 17.5602 | 3.41567 | 0.0111232 | 0.0808545 | 0.0032406 | 1(Win) | true |
| simdjson (ondemand) | 894.104 | 0.199756 | 7960.87ms | 4506446 | 80 | 7.37534e+09 | 4.80669e+06 | 0.132592 | 5.6785 | 21.9732 | 3.85896 | 0.0179059 | 0.0867825 | 0.00270331 | 2(Loss) | true |
