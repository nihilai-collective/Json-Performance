
----
### Instruments Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 975.533 | 0.0177697 | 9566.94ms | 183677 | 2560 | 2.60632e+06 | 179561 | 0.0224397 | 5.267 | 24.1524 | 4.78826 | 0.00564106 | 1.71284e-05 | 1.02209e-05 | 1(Win) | true |
| simdjson (ondemand) | 423.222 | 0.0786757 | 5344.44ms | 183677 | 640 | 6.78631e+07 | 413891 | 0.126817 | 12.0624 | 58.7412 | 10.5637 | 0.0377536 | 5.49198e-05 | 3.04202e-05 | 2(Loss) | true |
