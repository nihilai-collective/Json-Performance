
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11975.2 | 0.0345013 | 1392.35ms | 83958 | 4890 | 26021.9 | 6686.22 | 0.47954 | 0.43101 | 2.05559 | 0.0789086 | 5.14548e-05 | 2.67687e-06 | 6.23547e-07 | 1(Win) | true |
| simdjson (stage-1) | 11873.6 | 0.0421502 | 1377.39ms | 83958 | 160 | 1292.65 | 6743.43 | 0.0714168 | 0.428454 | 2.17586 | 0.0843755 | 7.15387e-05 | 1.2134e-05 | 9.52857e-06 | 2(Loss) | true |
