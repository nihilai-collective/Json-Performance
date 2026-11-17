
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16045 | 0.0429402 | 3485.12ms | 466906 | 640 | 90883.5 | 27751.7 | 0.0347044 | 0.315204 | 1.73857 | 0.0858482 | 2.13473e-05 | 5.78944e-07 | 1.03741e-07 | 1(Win) | true |
| simdjson (stage-1) | 13966.1 | 0.104568 | 3911.86ms | 466906 | 40 | 44459.4 | 31882.6 | 0.0481484 | 0.369083 | 1.74354 | 0.073925 | 2.17924e-05 | 3.39469e-05 | 3.36792e-05 | 2(Loss) | true |
