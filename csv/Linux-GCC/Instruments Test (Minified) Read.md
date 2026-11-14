
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11079.7 | 0.0609363 | 1654.72ms | 108313 | 320 | 10327.8 | 9322.94 | 0.0397699 | 0.466648 | 2.36527 | 0.101105 | 1.95614e-05 | 1.55798e-06 | 1.15406e-07 | 1(Win) | true |
| simdjson (stage-1) | 10309.5 | 0.0427905 | 1722.83ms | 108313 | 160 | 2941.04 | 10019.4 | 0.0732415 | 0.501644 | 2.66308 | 0.108962 | 4.24695e-05 | 2.30813e-06 | 0 | 2(Loss) | true |
