
----
### Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5866.07 | 0.172886 | 5256.58ms | 277673 | 30 | 182731 | 45142.6 | 0.109625 | 0.878328 | 3.9811 | 0.638841 | 0.00321205 | 3.00113e-06 | 1.80068e-06 | 1(Win) | true |
| simdjson (ondemand) | 4525.26 | 0.0620271 | 6590.4ms | 277673 | 160 | 210796 | 58518.1 | 0.0421487 | 1.13835 | 4.49958 | 0.721679 | 0.0039678 | 2.9261e-06 | 1.75566e-06 | 2(Loss) | true |
