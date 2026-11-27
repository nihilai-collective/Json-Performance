
----
### Google Maps Response Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1687.94 | 0.0679057 | 1305.31ms | 9378 | 2560 | 33140.5 | 5298.5 | 0.0630218 | 3.06484 | 13.5826 | 2.61442 | 0.00546887 | 4.92342e-05 | 2.97821e-05 | 1(Win) | true |
| simdjson (ondemand) | 1588.47 | 0.0399119 | 1319.34ms | 9378 | 4890 | 24693.2 | 5630.3 | 0.00546411 | 3.25907 | 14.5049 | 2.68629 | 0.00510984 | 3.93167e-05 | 1.77939e-05 | 2(Loss) | true |
