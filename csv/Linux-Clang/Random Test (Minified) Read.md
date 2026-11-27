
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13256.7 | 0.0765449 | 4058.33ms | 461466 | 640 | 413258 | 33197.4 | 0.0100639 | 0.387581 | 2.10669 | 0.147573 | 1.54061e-05 | 1.36454e-06 | 9.51451e-07 | 1(Win) | true |
| simdjson (stage-1) | 11599.8 | 0.0300657 | 4519.65ms | 461466 | 4890 | 636252 | 37939.2 | 0.0326572 | 0.441965 | 2.14087 | 0.0920285 | 1.39743e-05 | 5.27039e-06 | 4.5352e-06 | 2(Loss) | true |
