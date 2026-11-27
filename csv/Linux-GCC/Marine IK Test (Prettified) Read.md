
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 21836.5 | 0.082274 | 8281.07ms | 7351818 | 160 | 1.11653e+07 | 321079 | 0.039412 | 0.113369 | 1(Win) | true |
| simdjson (stage-1) | 17851.1 | 0.0648498 | 5152.88ms | 7351818 | 320 | 2.07599e+07 | 392762 | 0.0997789 | 0.138681 | 2(Loss) | true |
