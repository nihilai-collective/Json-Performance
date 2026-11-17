
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1344.82 | 0.0222094 | 990.07ms | 3862 | 4890 | 1809.16 | 2738.72 | 0.0837304 | 3.88927 | 18.1567 | 2.01605 | 0.000263434 | 3.73309e-05 | 3.81251e-06 | 1(Win) | true |
| simdjson (ondemand) | 740.802 | 0.0539043 | 1213.48ms | 3862 | 80 | 574.588 | 4971.76 | 0.0434767 | 7.01487 | 32.0163 | 3.55153 | 0.00258933 | 0.000100337 | 7.44433e-05 | 2(Loss) | true |
