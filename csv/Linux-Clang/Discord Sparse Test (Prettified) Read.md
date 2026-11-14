
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3266.09 | 0.0171668 | 3179.75ms | 83958 | 4890 | 86607.6 | 24515.1 | 0.133675 | 1.56892 | 7.19921 | 1.21805 | 0.00261522 | 4.05062e-06 | 1.20081e-06 | 1(Win) | true |
| simdjson (ondemand) | 2810.03 | 0.0288397 | 3578.07ms | 83958 | 2560 | 172871 | 28493.8 | 0.0537604 | 1.8325 | 7.42931 | 1.16355 | 0.00614419 | 8.90977e-06 | 3.88494e-06 | 2(Loss) | true |
