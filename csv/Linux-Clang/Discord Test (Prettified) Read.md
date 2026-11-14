
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13346.6 | 0.0471698 | 1316.78ms | 83958 | 4890 | 39158.2 | 5999.19 | 0.0262016 | 0.387092 | 2.08926 | 0.0970248 | 3.68161e-05 | 2.8157e-06 | 1.15697e-06 | 1(Win) | true |
| simdjson (stage-1) | 12610.8 | 0.0934905 | 1349.67ms | 83958 | 4890 | 172299 | 6349.21 | 0.0174809 | 0.409473 | 1.97265 | 0.0848163 | 4.38894e-05 | 2.18485e-06 | 5.45603e-07 | 2(Loss) | true |
