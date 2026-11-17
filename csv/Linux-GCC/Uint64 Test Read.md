
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1332.47 | 0.0425117 | 996.691ms | 3873 | 320 | 444.373 | 2771.98 | 0.00078914 | 3.92079 | 18.1479 | 2.00645 | 0.00129502 | 4.84121e-05 | 2.4206e-06 | 1(Win) | true |
| simdjson (ondemand) | 741.844 | 0.0555835 | 1215.87ms | 3873 | 1280 | 9803.27 | 4978.92 | 0.0554219 | 6.95914 | 31.7565 | 3.66357 | 0.00488337 | 7.16095e-05 | 2.05751e-05 | 2(Loss) | true |
