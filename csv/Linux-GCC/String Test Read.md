
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6346.42 | 0.0566863 | 857.698ms | 9578 | 640 | 426.018 | 1439.28 | 0.0137891 | 0.84989 | 4.19044 | 0.318229 | 0.000842752 | 8.48298e-06 | 1.30507e-06 | 1(Win) | true |
| simdjson (stage-1) | 3502.85 | 0.0426756 | 967.764ms | 9578 | 4890 | 6055.85 | 2607.68 | 0.00674352 | 1.49274 | 7.31009 | 0.54761 | 0.000923854 | 1.40702e-05 | 1.1743e-06 | 2(Loss) | true |
