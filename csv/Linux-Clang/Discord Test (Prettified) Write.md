
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15078.1 | 0.132926 | 1337.4ms | 94370 | 640 | 40287.9 | 5968.8 | 0.0606383 | 0.337247 | 1.33701 | 0.233538 | 0.000264004 | 1.20039e-05 | 5.91091e-06 | 1(Win) | true |
| Glaze | 3971.33 | 0.0772964 | 3011.76ms | 94370 | 2560 | 785517 | 22662 | 0.18627 | 1.2753 | 4.17865 | 0.678383 | 0.0015362 | 9.90947e-06 | 3.84126e-06 | 2(Loss) | true |
