
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21645.3 | 0.100202 | 6029.81ms | 5373214 | 320 | 1.80073e+07 | 236740 | 0.238372 | 0.114361 | 1(Win) | true |
| simdjson (stage-1) | 16508.3 | 0.262366 | 8196.67ms | 5373214 | 80 | 5.30603e+07 | 310407 | 0.2206 | 0.149957 | 2(Loss) | true |
