
----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11425 | 0.0920138 | 740.574ms | 2866 | 4890 | 236.948 | 239.232 | 0.0524404 | 0.529253 | 1.15701 | 0.182833 | 0.000349132 | 4.17418e-05 | 7.42076e-06 | 1(Win) | true |
| Glaze | 3748.69 | 0.176752 | 790.878ms | 2866 | 2560 | 4251.71 | 729.116 | 0.215998 | 1.45131 | 4.05373 | 0.675855 | 0.000360095 | 6.01066e-05 | 1.94904e-05 | 2(Loss) | true |
| simdjson (reflection) | 523.319 | 0.0789729 | 1249.71ms | 2866 | 4890 | 83192.6 | 5222.88 | 0.196582 | 9.92242 | 35.9198 | 7.52443 | 0.00753314 | 0.000165683 | 6.1364e-05 | 3(Loss) | true |
