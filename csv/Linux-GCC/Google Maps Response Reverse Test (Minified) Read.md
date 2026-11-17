
----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 768.894 | 0.0543103 | 2195.68ms | 11812 | 1280 | 81038 | 14650.6 | 0.0191721 | 6.64097 | 29.5995 | 6.03065 | 0.014809 | 6.48176e-05 | 3.7237e-05 | 1(Win) | true |
| simdjson (ondemand) | 713.074 | 0.0596975 | 2322.97ms | 11812 | 640 | 56920.7 | 15797.5 | 0.0546765 | 7.20933 | 31.8917 | 6.2489 | 0.0145092 | 2.72498e-05 | 1.09793e-05 | 2(Loss) | true |
