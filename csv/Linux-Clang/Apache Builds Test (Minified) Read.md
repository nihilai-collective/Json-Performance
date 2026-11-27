
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16692.3 | 0.0696278 | 1262.73ms | 94653 | 1280 | 18147.2 | 5407.76 | 0.0819229 | 0.311175 | 1.75871 | 0.117757 | 2.21615e-05 | 2.53393e-06 | 1.19681e-06 | 1(Win) | true |
| simdjson (stage-1) | 13612.3 | 0.0557099 | 1381.05ms | 94653 | 1280 | 17469.6 | 6631.39 | 0.0659189 | 0.381074 | 1.81521 | 0.0772084 | 2.71634e-05 | 2.65773e-06 | 1.51871e-06 | 2(Loss) | true |
