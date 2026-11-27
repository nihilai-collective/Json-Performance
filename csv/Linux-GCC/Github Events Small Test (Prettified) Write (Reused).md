
----
### Github Events Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13816.7 | 0.487063 | 735.75ms | 2866 | 4890 | 4539.67 | 197.821 | 0.145925 | 0.448366 | 0.98709 | 0.14201 | 0.000349561 | 2.14774e-05 | 8.63377e-06 | 1(Win) | true |
| Glaze | 4496.77 | 0.276761 | 780.268ms | 2866 | 4890 | 13837.9 | 607.821 | 0.181199 | 1.22272 | 3.3709 | 0.529658 | 0.000350774 | 2.92549e-05 | 9.13324e-06 | 2(Loss) | true |
| simdjson (reflection) | 523.512 | 0.115018 | 1249.48ms | 2866 | 2560 | 92314.3 | 5220.95 | 0.0437282 | 9.8604 | 35.4021 | 7.42272 | 0.00795902 | 0.000145701 | 4.83852e-05 | 3(Loss) | true |
