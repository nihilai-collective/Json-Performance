
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15239.6 | 0.0673373 | 3663.46ms | 466906 | 1280 | 495485 | 29218.3 | 0.0255661 | 0.335436 | 1.68483 | 0.0697443 | 7.13473e-06 | 7.74714e-07 | 2.96165e-07 | 1(Win) | true |
| simdjson (stage-1) | 13829.8 | 0.0325106 | 3932.35ms | 466906 | 1280 | 140246 | 32197 | 0.167702 | 0.368285 | 1.92737 | 0.0728648 | 3.12078e-05 | 3.26786e-06 | 2.53832e-06 | 2(Loss) | true |
