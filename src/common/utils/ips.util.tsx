import { NetworkInterfaceInfo, networkInterfaces } from 'os';

export const getLocalIpAddresses = (): string[] => {
  return Object.values(networkInterfaces())
    .reduce((result: string[], infos: NetworkInterfaceInfo[]) => {
      result.push(...infos.map(info => info.address));
      return result;
    }, []);
};
