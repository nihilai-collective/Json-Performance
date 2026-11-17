
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11077.5 | 0.0187342 | 1651.57ms | 108313 | 2560 | 7812.48 | 9324.77 | 0.0048596 | 0.466762 | 2.36527 | 0.101105 | 1.89447e-05 | 1.9042e-06 | 4.32774e-07 | 1(Win) | true |
| simdjson (stage-1) | 10298.8 | 0.0168214 | 1721.51ms | 108313 | 4890 | 13919.2 | 10029.8 | 0.00656665 | 0.502007 | 2.66308 | 0.108962 | 4.54318e-05 | 2.59983e-06 | 8.34512e-07 | 2(Loss) | true |
