
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12287.7 | 0.0364229 | 1378.89ms | 83958 | 4890 | 27545.1 | 6516.18 | 0.00936325 | 0.415523 | 2.1361 | 0.189369 | 2.49784e-05 | 2.79135e-06 | 7.79433e-08 | 1(Win) | true |
| simdjson (stage-1) | 11935.3 | 0.0669634 | 1395.88ms | 83958 | 80 | 1614.43 | 6708.52 | 0.101633 | 0.426915 | 2.17586 | 0.0843755 | 3.87098e-05 | 6.69978e-06 | 5.95536e-07 | 2(Loss) | true |
