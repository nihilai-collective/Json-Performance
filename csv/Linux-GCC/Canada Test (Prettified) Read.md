
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22859.1 | 0.118041 | 5730.65ms | 5373214 | 160 | 1.12029e+07 | 224169 | 0.018345 | 0.108291 | 1(Win) | true |
| simdjson (stage-1) | 16109.1 | 0.10265 | 8170.53ms | 5373214 | 160 | 1.70593e+07 | 318099 | 0.16614 | 0.153673 | 2(Loss) | true |
