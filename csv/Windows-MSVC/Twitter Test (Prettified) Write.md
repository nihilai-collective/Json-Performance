
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3905.46 | 0.188839 | 9186.04ms | 716365 | 2560 | 2.79351e+08 | 174929 | 0.795073 | 0.633515 | 1(Win) | true |
| Glaze | 2343.08 | 0.31734 | 7331.33ms | 716365 | 1280 | 1.09586e+09 | 291574 | 0.61933 | 1.05619 | 2(Loss) | true |
