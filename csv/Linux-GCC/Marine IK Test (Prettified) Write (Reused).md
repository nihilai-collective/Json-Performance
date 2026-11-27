
----
### Marine IK Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 6019.85 | 0.296139 | 5017.84ms | 10018896 | 160 | 3.53491e+09 | 1.58721e+06 | 1.43436 | 0.41123 | 1(Win) | true |
| Glaze | 3712.99 | 0.107961 | 8012.53ms | 9930228 | 160 | 1.21318e+09 | 2.55056e+06 | 0.696707 | 0.66676 | 2(Loss) | true |
| simdjson (reflection) | 276.3 | 2.75653 | 10222.5ms | 10018896 | 30 | 2.72601e+13 | 3.45812e+07 | 2.26206 | 8.96049 | 3(Loss) | true |
