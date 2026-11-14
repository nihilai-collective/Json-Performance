
----
### Google Maps Response Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3900.55 | 0.0378365 | 970.435ms | 9378 | 4890 | 3680.44 | 2292.9 | 0.0030059 | 1.34314 | 5.80657 | 0.975155 | 0.00135635 | 1.3171e-05 | 1.30837e-07 | 1(Win) | true |
| simdjson (ondemand) | 3657.78 | 0.0303544 | 987.536ms | 9378 | 4890 | 2693.63 | 2445.08 | 0.0886559 | 1.43108 | 6.17797 | 0.91896 | 0.0015571 | 1.66818e-05 | 2.22424e-06 | 2(Loss) | true |
