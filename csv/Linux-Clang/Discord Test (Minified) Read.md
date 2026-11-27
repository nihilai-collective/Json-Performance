
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11429.6 | 0.0466273 | 1190.54ms | 56369 | 1280 | 6156.15 | 4703.37 | 0.0470296 | 0.45454 | 2.37219 | 0.170856 | 3.60349e-05 | 2.03736e-06 | 5.54383e-08 | 1(Win) | true |
| simdjson (stage-1) | 10414.7 | 0.0564417 | 1234.72ms | 56369 | 1280 | 10864.1 | 5161.69 | 0.127762 | 0.498646 | 2.3721 | 0.103674 | 3.62982e-05 | 2.23139e-06 | 2.49472e-07 | 2(Loss) | true |
