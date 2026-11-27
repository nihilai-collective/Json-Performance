
----
### Google Maps Response Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4202.87 | 0.0376941 | 1305.63ms | 25388 | 2560 | 12071.3 | 5760.8 | 0.131313 | 1.22608 | 5.673 | 0.930794 | 0.00191434 | 9.32404e-06 | 2.64643e-06 | 1(Win) | true |
| simdjson (ondemand) | 3952.46 | 0.0696352 | 1337.62ms | 25388 | 1280 | 23291.1 | 6125.77 | 0.0452188 | 1.30586 | 5.97255 | 0.887073 | 0.00187724 | 9.87794e-06 | 2.80029e-06 | 2(Loss) | true |
