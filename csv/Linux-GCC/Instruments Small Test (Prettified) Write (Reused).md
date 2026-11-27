
----
### Instruments Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 28498.2 | 0.111743 | 747.402ms | 9249 | 80 | 9.56946 | 309.512 | 0.293952 | 0.207622 | 0.672721 | 0.0768732 | 0.00010812 | 2.70299e-06 | 0 | 1(Win) | true |
| Glaze | 3867.36 | 0.190044 | 947.037ms | 9249 | 4890 | 91870.8 | 2280.76 | 0.389323 | 1.36424 | 3.52752 | 0.565359 | 0.000427239 | 1.59858e-05 | 4.48841e-06 | 2(Loss) | true |
| simdjson (reflection) | 522.592 | 0.0689174 | 2415.71ms | 9249 | 4890 | 661654 | 16878.4 | 0.226167 | 9.85696 | 40.8179 | 8.29468 | 0.0145816 | 0.000108297 | 5.21805e-05 | 3(Loss) | true |
