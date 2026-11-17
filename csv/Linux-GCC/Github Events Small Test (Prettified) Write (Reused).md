
----
### Github Events Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19836.5 | 0.115589 | 16.2903ms | 2866 | 1280 | 32.4688 | 137.788 | 0.0130425 | 0.100621 | 1(Win) | true |
| Glaze | 5268.37 | 0.193945 | 54.8351ms | 2866 | 30 | 30.3724 | 518.8 | 0.320225 | 0.444208 | 2(Loss) | true |
| simdjson (reflection) | 555.608 | 0.096798 | 484.416ms | 2866 | 40 | 907.003 | 4919.35 | 0.181604 | 4.43112 | 3(Loss) | true |
