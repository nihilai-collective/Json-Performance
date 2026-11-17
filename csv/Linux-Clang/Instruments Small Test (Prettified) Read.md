
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2233.28 | 0.0457772 | 1064.57ms | 7932 | 4890 | 11756.7 | 3387.19 | 0.0556946 | 2.31167 | 10.2089 | 1.48512 | 0.000968457 | 2.83081e-05 | 8.7915e-06 | 1(Win) | true |
| Jsonifier (generic) | 2098.52 | 0.163312 | 1084.05ms | 7932 | 30 | 1039.67 | 3604.7 | 0.059147 | 2.44587 | 9.50895 | 1.81631 | 0.00165154 | 1.68095e-05 | 0 | 2(Loss) | true |
