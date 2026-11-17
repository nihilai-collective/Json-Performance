
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1912.41 | 0.0506887 | 860.416ms | 2632 | 1280 | 566.558 | 1312.52 | 0.0666807 | 2.76757 | 11.0638 | 2.01064 | 0.000772345 | 2.96828e-05 | 5.63972e-06 | 1(Win) | true |
| simdjson (ondemand) | 1520.05 | 0.044497 | 887.289ms | 2632 | 4890 | 2640.15 | 1651.31 | 0.154323 | 3.44457 | 11.6337 | 2.13944 | 0.00319001 | 6.78296e-05 | 1.94243e-05 | 2(Loss) | true |
