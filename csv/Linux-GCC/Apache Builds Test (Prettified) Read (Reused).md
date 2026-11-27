
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2899.04 | 0.063779 | 6065.46ms | 124597 | 320 | 218681 | 40987.7 | 0.03191 | 1.748 | 8.39641 | 1.48486 | 0.00439201 | 4.99109e-06 | 2.43284e-06 | 1(Win) | true |
| simdjson (ondemand) | 2162.66 | 0.0580209 | 7487.13ms | 124597 | 320 | 325205 | 54943.8 | 0.0346724 | 2.34722 | 9.51904 | 1.71908 | 0.00674959 | 1.14369e-05 | 6.82199e-06 | 2(Loss) | true |
