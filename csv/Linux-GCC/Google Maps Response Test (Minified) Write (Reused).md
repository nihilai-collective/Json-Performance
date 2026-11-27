
----
### Google Maps Response Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13888.4 | 0.0354872 | 814.069ms | 11812 | 2560 | 212.092 | 811.093 | 0.0833442 | 0.38355 | 1.82586 | 0.210718 | 8.46597e-05 | 2.26861e-05 | 6.81246e-06 | 1(Win) | true |
| simdjson (reflection) | 10296.7 | 0.0565887 | 844.475ms | 11812 | 320 | 122.648 | 1094.02 | 0.0824828 | 0.510296 | 2.28149 | 0.332205 | 0.000107677 | 2.67207e-05 | 0 | 2(Loss) | true |
| Glaze | 5067.77 | 0.149941 | 957.913ms | 11812 | 2560 | 28437.7 | 2222.83 | 0.0441071 | 1.01723 | 4.35083 | 0.655943 | 0.000100236 | 1.5543e-05 | 5.48965e-06 | 3(Loss) | true |
