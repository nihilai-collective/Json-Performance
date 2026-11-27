
----
### Google Maps Response Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2404.12 | 0.0955719 | 1101.54ms | 9378 | 2560 | 32360.1 | 3720.1 | 0.0339488 | 2.14455 | 9.43954 | 1.64683 | 0.0010555 | 3.95707e-05 | 1.24543e-05 | 1(Win) | true |
| simdjson (ondemand) | 2091 | 0.159751 | 1158.56ms | 9378 | 30 | 1400.63 | 4277.17 | 0.109226 | 2.44637 | 10.1507 | 1.67914 | 0.00141821 | 2.84353e-05 | 1.06633e-05 | 2(Loss) | true |
